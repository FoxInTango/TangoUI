#include <string>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <wayland-server.h>
#include <wayland-client.h>
#include <wayland-server-protocol.h>
#include <libseat.h>
#include <drm.h>
#include <fcntl.h>
#include <errno.h>
int tango_as_server();
int tango_as_client();

libseat* seat = 0;

int libseat_init(libseat*& s){
    char* deviceNode = "/dev/dri/card1";
    int fd = open(deviceNode, O_RDWR | O_CLOEXEC, 0);
    if(!fd) printf("can't open : %s error:%s\n",deviceNode,strerror(errno));

    return fd;
} 

int
main(int argc, char *argv[])
{
    if(argc > 1) {
        if(std::string(argv[1]) == "server") return tango_as_server();
        else if (std::string(argv[1]) == "client") return tango_as_client();
    }
    libseat_init(seat);

    
    tango_as_server();
    tango_as_client();
    return 0;
}
static void compositor_create_surface(struct wl_client* client, struct wl_resource* resource, uint32_t id);

static void compositor_create_region(struct wl_client* client, struct wl_resource* resource, uint32_t id);

static const struct wl_compositor_interface compositor_impl = {
    .create_surface = compositor_create_surface,
    .create_region = compositor_create_region,
};
// wlroots/types/wlr_compositor.c 1314:
static void compositor_create_surface(struct wl_client* client,struct wl_resource* resource, uint32_t id) {
    if (client) printf("compositor_create_surface\n");
    //struct wlr_compositor* compositor = compositor_from_resource(resource);
    // wlroots/types/wlr_compositor.c 1307 : 
    //static struct wlr_compositor* compositor_from_resource( struct wl_resource* resource) {
        assert(wl_resource_instance_of(resource, &wl_compositor_interface,&compositor_impl));
        void* user_data = wl_resource_get_user_data(resource);
    //}
    // wlroots/types/wlr_compositor.c 1314 ;
    /*
    struct wlr_surface* surface = surface_create(client,
        wl_resource_get_version(resource), id, compositor);
    if (surface == NULL) {
        wl_client_post_no_memory(client);
        return;
    }
    
    wl_signal_emit_mutable(&compositor->events.new_surface, surface);
    */
}
// wlroots/types/wlr_compositor.c 1314 ;

static void compositor_create_region(struct wl_client* client,struct wl_resource* resource, uint32_t id) {
    if(client) printf("compositor_create_region\n");
}

struct tango_compositor{
char* name;
struct wl_display*   display;
struct wl_global*    global;
struct {
    struct wl_signal new_surface;
    struct wl_signal destroy;
} events;

struct {
    struct wl_listener display_destroy;
    struct wl_listener renderer_destroy;
};
};

//https://wayland.arktoria.org/5-registry/server-side.html
static void
wl_compositor_handle_bind(struct wl_client* client, void* data,uint32_t version, uint32_t id)
{
    struct tango_compositor* compositor = (struct tango_compositor*)data;
    printf("__fucntion : %s id : %d\n", compositor->name, id);
    
    // wlroots/types/wlr_compositor.c 1343
    struct wl_resource* resource = wl_resource_create(client,&wl_compositor_interface, version, id);
    if (resource == NULL) {
        wl_client_post_no_memory(client);
        return;
    }
    wl_resource_set_implementation(resource, &compositor_impl, compositor, NULL);
}

static void compositor_handle_display_destroy(struct wl_listener* listener, void* data) {
    struct tango_compositor* compositor = wl_container_of(listener, compositor, display_destroy);
    wl_signal_emit_mutable(&compositor->events.destroy, NULL);

    assert(wl_list_empty(&compositor->events.new_surface.listener_list));
    assert(wl_list_empty(&compositor->events.destroy.listener_list));

    wl_list_remove(&compositor->display_destroy.link);
    wl_list_remove(&compositor->renderer_destroy.link);
    wl_global_destroy(compositor->global);
}

int tango_as_server() { 
    struct wl_display  *display  = wl_display_create();
    if (!display) {
        fprintf(stderr, "Unable to create Wayland display.\n");
        return 1;
    }
    
    struct tango_compositor compositor;
    compositor.name = "TangoWL";
    compositor.display = display;
    // notice the version problem. wlroots/wlr_compositor assert(version <= COMPOSITOR_VERSION);
    //  libwayland : build/src/wayland-protocol.c : wl_interface wl_compositor_interface
    compositor.global = wl_global_create(compositor.display,&wl_compositor_interface,5, &compositor, wl_compositor_handle_bind); 
    if (!compositor.global) {
        fprintf(stderr, "wl_global_create failed.\n");
        return 1;
    }
    wl_signal_init(&compositor.events.new_surface);
    wl_signal_init(&compositor.events.destroy);
    compositor.display_destroy.notify = compositor_handle_display_destroy;
    wl_display_add_destroy_listener(display, &compositor.display_destroy);
    const char *socket = wl_display_add_socket_auto(display);
    if (!socket) {
        fprintf(stderr, "Unable to add socket to Wayland display.\n");
        return 1;
    }

    fprintf(stderr, "Running Wayland display on %s\n", socket);
    wl_display_run(display);

    wl_display_destroy(display);
    return 0;
}
wl_compositor* client_compositor;
static void
registry_handle_global(void* data, struct wl_registry* registry,
    uint32_t name, const char* interface, uint32_t version)
{
    printf("interface: '%s', version: %d, name: %d\n",
        interface, version, name);
    client_compositor = (wl_compositor*)wl_registry_bind(registry, name, &wl_compositor_interface, 4); 
    struct wl_surface* surface = wl_compositor_create_surface(client_compositor);
    if(surface) printf("surface created.\n");
}

static void
registry_handle_global_remove(void* data, struct wl_registry* registry,
    uint32_t name)
{
    // This space deliberately left blank
}
// https://wayland.arktoria.org/5-registry/binding.html
static const struct wl_registry_listener registry_listener = {
    .global = registry_handle_global,
    .global_remove = registry_handle_global_remove,
};


int tango_as_client()
{
    struct wl_display* display = wl_display_connect("wayland-0");
    if (!display) {
        fprintf(stderr, "Failed to connect to Wayland display.\n");
        return 1;
    }
    struct wl_registry* registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);
    wl_display_roundtrip(display);
    
    wl_display_disconnect(display);
    return 0;
}