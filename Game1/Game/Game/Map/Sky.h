#pragma once

class Sky : public GameObject
{
public:

	Sky();

	~Sky();


	void Start()override;

	void Update()override;

	void Render()override;
private:

	SkinModel		m_skinModel;
	SkinModelData	m_skinModelData;
	Light			m_light;
};