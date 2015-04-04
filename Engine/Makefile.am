AM_CPPFLAGS = -Iinclude
AM_LDFLAGS = $(LIBFLAGS)

lib_LTLIBRARIES = $(top_builddir)/lib/libEngine.la

__top_builddir__lib_libEngineincludedir = $(includedir)/Engine-GL4-
__top_builddir__lib_libEngineinclude_HEADERS = \
	include/Engine/Input.hpp \
	include/Engine/Light.hpp \
	include/Engine/Texture.hpp \
	include/Engine/Texture2D.hpp \
	include/Engine/TextureCube.hpp \
	include/Engine/Buffer.hpp \
	include/Engine/DepthMap.hpp \
	include/Engine/ParticlesManager.hpp \
	include/Engine/Camera.hpp \
	include/Engine/Mesh.hpp \
	include/Engine/DirLight.hpp \
	include/Engine/Renderer.hpp \
	include/Engine/MovableCamera.hpp \
	include/Engine/Model.hpp \
	include/Engine/SkyBox.hpp \
	include/Engine/PlayerCam.hpp \
	include/Engine/FrameBuffer.hpp \
	include/Engine/GBuffer.hpp \
	include/Engine/EngineHead.hpp \
	include/Engine/Screen.hpp \
	include/Engine/TextArray.hpp \
	include/Engine/SpotLight.hpp \
	include/Engine/FreeCam.hpp \
	include/Engine/OctreeSystem.hpp \
	include/Engine/ShaderProgram.hpp \
	include/Engine/Object.hpp \
	include/Engine/Audio.hpp \
	include/Engine/Sound.hpp

__top_builddir__lib_libEngine_la_SOURCES = \
	src/Buffer.cpp \
	src/DepthMap.cpp \
	src/Model.cpp \
	src/Renderer.cpp \
	src/Mesh.cpp \
	src/DirLight.cpp \
	src/GBuffer.cpp \
	src/Object.cpp \
	src/Screen.cpp \
	src/FrameBuffer.cpp \
	src/MovableCamera.cpp \
	src/Camera.cpp \
	src/PlayerCam.cpp \
	src/ShaderProgram.cpp \
	src/OctreeSystem.cpp \
	src/SkyBox.cpp \
	src/Light.cpp \
	src/Texture.cpp \
	src/Texture2D.cpp \
	src/TextureCube.cpp \
	src/Input.cpp \
	src/TextArray.cpp \
	src/FreeCam.cpp \
	src/SpotLight.cpp \
	src/ParticlesManager.cpp \
	src/Audio.cpp \
	src/Sound.cpp

clean-local:
	rm -f include/Engine/*~ src/*~
