AM_CPPFLAGS = -Iinclude
AM_LDFLAGS =

lib_LTLIBRARIES = $(top_builddir)/lib/libEngine.la

__top_builddir__lib_libEngine_la_LIBADD = $(ENGINE_LIBSFLAGS)

__top_builddir__lib_libEngine_la_includedir = $(includedir)/Engine-GL4-

__top_builddir__lib_libEngine_la_include_HEADERS = \
	include/Engine/Object.hpp \
	include/Engine/Input/InputManager.hpp \
	include/Engine/Audio/Sound.hpp \
	include/Engine/Audio/AudioRenderer.hpp \
	include/Engine/Graphics/DirLight.hpp \
	include/Engine/Graphics/SkeletalMesh.hpp \
	include/Engine/Graphics/Window.hpp \
	include/Engine/Graphics/SpotLight.hpp \
	include/Engine/Graphics/FreeCam.hpp \
	include/Engine/Graphics/Material.hpp \
	include/Engine/Graphics/GraphicsRenderer.hpp \
	include/Engine/Graphics/Camera.hpp \
	include/Engine/Graphics/MovableCamera.hpp \
	include/Engine/Graphics/Skeleton.hpp \
	include/Engine/Graphics/DepthMap.hpp \
	include/Engine/Graphics/SkyBox.hpp \
	include/Engine/Graphics/Mesh.hpp \
	include/Engine/Graphics/Octree.hpp \
	include/Engine/Graphics/StaticModel.hpp \
	include/Engine/Graphics/PerspCamera.hpp \
	include/Engine/Graphics/Screen.hpp \
	include/Engine/Graphics/StaticMesh.hpp \
	include/Engine/Graphics/ParticlesManager.hpp \
	include/Engine/Graphics/TextArray.hpp \
	include/Engine/Graphics/SkeletalModel.hpp \
	include/Engine/Graphics/OrthoCamera.hpp \
	include/Engine/Graphics/Texture2D.hpp \
	include/Engine/Graphics/ShaderProgram.hpp \
	include/Engine/Graphics/Model.hpp \
	include/Engine/Graphics/Buffer.hpp \
	include/Engine/Graphics/Light.hpp \
	include/Engine/Graphics/PlayerCam.hpp \
	include/Engine/Graphics/Texture.hpp \
	include/Engine/Graphics/GBuffer.hpp \
	include/Engine/Graphics/FrameBuffer.hpp \
	include/Engine/Graphics/TextureCube.hpp \
	include/Engine/Tools/StringManager.hpp

__top_builddir__lib_libEngine_la_SOURCES = \
	src/Input/InputManager.cpp \
	src/Audio/Sound.cpp \
	src/Audio/AudioRenderer.cpp \
	src/Graphics/ShaderProgram.cpp \
	src/Graphics/Octree.cpp \
	src/Graphics/Screen.cpp \
	src/Graphics/Material.cpp \
	src/Graphics/Texture.cpp \
	src/Graphics/PlayerCam.cpp \
	src/Graphics/DepthMap.cpp \
	src/Graphics/MovableCamera.cpp \
	src/Graphics/TextArray.cpp \
	src/Graphics/FreeCam.cpp \
	src/Graphics/Camera.cpp \
	src/Graphics/Texture2D.cpp \
	src/Graphics/Window.cpp \
	src/Graphics/OrthoCamera.cpp \
	src/Graphics/PerspCamera.cpp \
	src/Graphics/Skeleton.cpp \
	src/Graphics/StaticModel.cpp \
	src/Graphics/SkyBox.cpp \
	src/Graphics/GBuffer.cpp \
	src/Graphics/SkeletalMesh.cpp \
	src/Graphics/SpotLight.cpp \
	src/Graphics/TextureCube.cpp \
	src/Graphics/Buffer.cpp \
	src/Graphics/Mesh.cpp \
	src/Graphics/SkeletalModel.cpp \
	src/Graphics/StaticMesh.cpp \
	src/Graphics/DirLight.cpp \
	src/Graphics/Model.cpp \
	src/Graphics/GraphicsRenderer.cpp \
	src/Graphics/Light.cpp \
	src/Graphics/FrameBuffer.cpp \
	src/Graphics/ParticlesManager.cpp \
	src/Tools/StringManager.cpp \
	src/Tools/private/AssimpTool.cpp \
	src/Object.cpp

clean-local:
	rm -f *~
	rm -f src/*~
	rm -f include/Engine/*~
