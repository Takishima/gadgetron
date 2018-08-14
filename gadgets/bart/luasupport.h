


#define LUA_HELPER_FUNCTIONS "function bartShowToTable(str)                                     \n\
                                      if str == nil then return nil end                         \n \
                                      local tableOut = {}                                       \n\
                                      local typeStr = str:match(\"Type:%s*([^\\n]+)\")          \n\
                                      local nDims = tonumber(str:match(\"Dimensions:%s*(%d+)\"))\n\
                                      local AoDStr = str:match(\"AoD:%s*([^\\n]+)\")            \n\
                                      local curDim = 0                                          \n\
                                      for dimSize in AoDStr:gmatch(\"%d+\") do                  \n\
                                              tableOut[curDim] = tonumber(dimSize)              \n\
                                              curDim = curDim+1                                 \n\
                                      end                                                       \n\
                                      tableOut.nDims = nDims                                    \n\
                                      tableOut.type = typeStr                                   \n\
                                      return tableOut                                           \n \
                              end                                                               \n \
                                                                                                \n \
                              function show(str)                                                \n \
                                      return bartShowToTable(bart(\"show -m \" .. str))         \n \
                              end																\n \
							  																	\n \
							  function registerOutput(str)										\n \
							  		  _outputDatasetName = str 									\n \
							  end"

#define LUA_ERR_FAIL(msg) GERROR_STREAM(msg); lua_close(lua_state); return GADGET_FAIL
#define LUA_REGISTER_PARAM(PARAM) lua_pushnumber(lua_state, dp.PARAM); lua_setglobal(lua_state, #PARAM)

inline Gadgetron::BartGadget *lua_getgadget(lua_State *L)
{
	lua_getglobal(L, "_bartGadget");
	auto gadget = static_cast<Gadgetron::BartGadget *>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	return gadget;
}

// GDEBUG wrapper
int lua_gdebug(lua_State *L)
{
	// gets first argument (string)
	const char *outString = luaL_checkstring(L,1);

	auto gadget = lua_getgadget(L);
	if (outString) // there is a string
	{
		gadget->local_gdebug(outString);
	}
	else // print out an empy ICE_OUT
	{
		gadget->local_gdebug("");
	}
	return 0; // no return values to lua
}

int lua_ginfo(lua_State *L)
{
	// gets first argument (string)
	const char *outString = luaL_checkstring(L,1);
	auto gadget = lua_getgadget(L);
	if (outString) // there is a string
	{
		gadget->local_ginfo(outString);
	}
	else // print out an empy ICE_OUT
	{
		gadget->local_ginfo("");
	}
	return 0; // no return values to lua
}

// calling bart from lua - return nil if error; returns string (either empty or not) if success
int lua_bart(lua_State *lua_state)
{
	std::string outStr("");
	
	auto res = Gadgetron::call_BART(luaL_checkstring(lua_state,1), outStr); 
	if (res) // call_BART returns true in case of success
		lua_pushstring(lua_state, outStr.c_str());
	else
		lua_pushnil(lua_state);
	return 1;
}


