#pragma once


enum EnCollisionAttr {
	enCollisionAttr_Unknown = -1,
	enCollisionAttr_Ground,
	enCollisionAttr_Character,
	enCollisionAttr_MoveFloor,
	enCollisionAttr_Spring,
	enCollisionAttr_Rotation,
	enCollisionAttr_Detection,
	enCollisionAttr_MapChip,
	enCollisionAttr_User,		//以下にユーザー定義のコリジョン属性を設定する。
};

enum EnJudgmentColl
{
	enJudgment_Wall,
	enJudgment_Ground,
};