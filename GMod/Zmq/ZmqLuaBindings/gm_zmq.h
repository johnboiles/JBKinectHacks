
//GMOD_MODULE( Lzmq_init, Lzmq_close );
extern "C" {
int Lzmq_version(lua_State *L);

int Lzmq_push_error(lua_State *L);

int Lzmq_init(lua_State *L);

int Lzmq_term(lua_State *L);

int Lzmq_ctx_gc(lua_State *L);

int Lzmq_ctx_lightuserdata(lua_State *L);

int Lzmq_socket(lua_State *L);

int Lzmq_close(lua_State *L);

int Lzmq_setsockopt(lua_State *L);

int Lzmq_getsockopt(lua_State *L);

int Lzmq_bind(lua_State *L);

int Lzmq_connect(lua_State *L);

int Lzmq_send(lua_State *L);
int Lzmq_recv(lua_State *L);

LUALIB_API int luaopen_zmq(lua_State *L);

}