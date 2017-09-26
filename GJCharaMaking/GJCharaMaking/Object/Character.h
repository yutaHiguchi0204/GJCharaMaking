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

	void LoadModel();      //���f���f�[�^�̓ǂݍ���

	void SetParentModel(); //���f���̐e�q�֌W���\�z

	void SetOfset();       //���f���̃I�t�Z�b�g���Z�b�g
private:
	std::vector<Character> partsnumber_ ; //�p�[�c�ԍ�

};