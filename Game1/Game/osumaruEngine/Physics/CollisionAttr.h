#pragma once


enum EnCollisionAttr {
	enCollisionAttr_Ground,
	enCollisionAttr_Character,
	enCollisionAttr_MoveFloor,
	enCollisionAttr_Spring,
	enCollisionAttr_CliffDetection,
	enCollisionAttr_User,		//以下にユーザー定義のコリジョン属性を設定する。
};