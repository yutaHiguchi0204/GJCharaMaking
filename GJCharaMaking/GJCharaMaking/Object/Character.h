/*===============================================================
// @param	[Character] class header
// @create	Yuki Matsumaru
// @date	17/09/26
================================================================*/

#pragma once

// including header
#include <vector>

//class
class Character 
{
public:
	Character();
	~Character();

	void Initialize();
	void Update();
	void Draw();

	void LoadModel();      //モデルデータの読み込み

	void SetParentModel(); //モデルの親子関係を構築

	void SetOfset();       //モデルのオフセットをセット
private:
	std::vector<Character> partsnumber_ ; //パーツ番号

};