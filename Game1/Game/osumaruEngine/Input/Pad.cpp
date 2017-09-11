#include "engineStdafx.h"
#include "Pad.h"

const int triggerMax = 255;

struct CorrespondencePad
{
	PadButton	padButton;
	DWORD		padCode;
	DWORD		keyCode;
};

const CorrespondencePad correspondencePad[padButtonNum] = 
{
	{ padButtonUp,			XINPUT_GAMEPAD_DPAD_UP,			'W' },
	{ padButtonDown,		XINPUT_GAMEPAD_DPAD_DOWN,		'S' },
	{ padButtonLeft,		XINPUT_GAMEPAD_DPAD_LEFT,		'A' },
	{ padButtonRight,		XINPUT_GAMEPAD_DPAD_RIGHT,		'D' },
	{ padButtonA,			XINPUT_GAMEPAD_A,				'J' },
	{ padButtonB,			XINPUT_GAMEPAD_B,				'K' },
	{ padButtonX,			XINPUT_GAMEPAD_X,				'I' },
	{ padButtonY,			XINPUT_GAMEPAD_Y,				'O' },
	{ padButtonStart,		XINPUT_GAMEPAD_START,			'B' },
	{ padButtonSelect,		XINPUT_GAMEPAD_BACK,			'V' },
	{ padButtonRB,			XINPUT_GAMEPAD_RIGHT_SHOULDER,	'2' },
	{ padButtonRStickPush,	XINPUT_GAMEPAD_RIGHT_THUMB,		'4' },
	{ padButtonLB,			XINPUT_GAMEPAD_LEFT_SHOULDER,	'7' },
	{ padButtonLStickPush,	XINPUT_GAMEPAD_LEFT_THUMB,		'9' }
};
Pad::Pad()
{
	m_padNum = 0;
	for (bool& isPad : m_isPadPress)
	{
		isPad = false;
	}
	m_rightStickX = 0.0f;
	m_rightStickY = 0.0f;
	m_leftStickX = 0.0f; 
	m_leftStickY = 0.0f;
	m_rightTrigger = 0.0f;
	m_leftTrigger = 0.0f;
}

Pad::~Pad()
{

}

void Pad::Update()
{
	DWORD result = XInputGetState(m_padNum, &m_state);

	if (result == ERROR_SUCCESS)
	{
		for (const CorrespondencePad& pad : correspondencePad)
		{
			if (m_state.Gamepad.wButtons & pad.padCode)
			{
				m_isPadPress[pad.padButton] = true;
			}
			else
			{
				m_isPadPress[pad.padButton] = false;
			}
		}
		float inputNormalize;
		inputNormalize = triggerMax;
		//ÉgÉäÉKÅ[ÇÃâüÇµçûÇ›ó Ç0.0Å`1.0Ç…ê≥ãKâª
		m_leftTrigger = (float)m_state.Gamepad.bLeftTrigger / inputNormalize;
		m_rightTrigger = (float)m_state.Gamepad.bRightTrigger / inputNormalize;

		const int stickNum = 4;
		float padInput[stickNum] = 
		{
			m_state.Gamepad.sThumbLX,
			m_state.Gamepad.sThumbLY,
			m_state.Gamepad.sThumbRX,
			m_state.Gamepad.sThumbRY,
		};
		float* padOutput[stickNum] = 
		{
			&m_leftStickX,
			&m_leftStickY,
			&m_rightStickX,
			&m_rightStickY,
		};
		for (int i = 0; i < stickNum; i++)
		{
			if (0 < padInput)
			{
				inputNormalize = SHRT_MAX;
			}
			else
			{
				inputNormalize = -SHRT_MIN;
			}
			//ÉXÉeÉBÉbÉNÇÃì¸óÕó Ç-1.0Å`1.0Ç…ê≥ãKâª
			*padOutput[i] = padInput[i] / inputNormalize;
		}

	}
	else
	{

	}
}