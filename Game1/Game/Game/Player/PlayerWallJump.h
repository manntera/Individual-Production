#pragma once
//プレイヤーの壁ずりや壁ジャンプをするクラス
class Player;


class PlayerWallJump
{
public:

	PlayerWallJump();

	~PlayerWallJump();

	void Init(Player* player, CharacterController* characterController);

	void Update();

	bool IsWallShear()
	{
		return m_isWallShear;
	}

	bool IsWallJump()
	{
		return m_isWallJump;
	}

private:
	BoxCollider				m_boxCollider;
	CollisionDetection		m_wallDetection;
	Player*					m_player;
	bool					m_isWallShear;
	bool					m_isWallJump;
	CharacterController*	m_characterController;
	D3DXVECTOR3				m_wallJumpDirection;
};