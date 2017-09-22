#pragma once
class Player : public GameObject
{
public:

	Player();

	~Player();

	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation);

	void Update() override;

	void Start() override;

	void Render() override;

	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
private:
	SkinModel			m_skinModel;
	SkinModelData		m_skinModelData;
	Light				m_light;
	D3DXQUATERNION		m_rotation;
	D3DXVECTOR3			m_position;
	D3DXVECTOR3			m_scale;
	Animation			m_anim;
	CharacterController m_characterController;
	Texture				m_modelNormalMap;
	Texture				m_modelSpecularMap;
};