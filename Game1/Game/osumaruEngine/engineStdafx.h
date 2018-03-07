#pragma once
class EffectManager;
int MakeHash(const char* string);

#include <d3d9.h>
#include <d3dx9effect.h>
#include <windows.h>
#include <x3daudio.h>
#include <XAudio2.h>
#include <XAudio2fx.h>
#include <mmsystem.h>
#include <XInput.h>
#include <cstdlib>
#include <memory>
#include <vector>
#include <map>
#include <list>

#include <string>
#include <typeinfo>

#pragma comment ( lib, "winmm.lib" )

#include <stdio.h>
#include <string.h>

#include "Timer\GameTime.h"
#include "Random\Random.h"
#include "Uncopyable.h"
#include "Graphics/Texture.h"
#include "Graphics/Primitive.h"
#include "Graphics/RenderTarget.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectManager.h"
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"