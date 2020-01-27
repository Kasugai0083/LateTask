#include "SingletonTemplate.h"
#include <iostream> 

class Hoge : public Singleton<Hoge> {
//クラスの実態
public:
	void SetPos(int x_, int y_){ x = x_; y = y_; }
	int GetPosX() const { return x; }
	int GetPosY() const { return y; }

protected:
	int x, y;

//シングルトンテンプレートを使うための宣言部
private:
	//シングルトンテンプレートに自身（Hoge）を指定したものだけ、
	//特別にprivate,protectedにアクセスできるようにする
	friend Singleton<Hoge>;

	Hoge() {};
	virtual ~Hoge() {};

	//コピーコンストラクタの禁止
	Hoge(const Hoge&) = delete;
	Hoge& operator=(const Hoge&) = delete;
	//ムーブコンストラクタの禁止
	Hoge(const Hoge&&) = delete;
	Hoge& operator=(const Hoge&&) = delete;

};


//class Foo : public Hoge {
//public:
//	Foo() {};
//	~Foo() {};
//
//	void SetPosZ(int z_) { z = z_; }
//	int GetPosZ() const { return z; }
//
//private:
//	int z;
//
//};

void main() {

	Hoge::CreateInstance();	//シングルトンの実態を作成
	
	// Hoge* phoge2 = new Hoge(); // 直接newすることはできない
	// Hoge* phoge2 = new Hoge(*Hoge::GetInstance());

	{
		Hoge* phoge = Hoge::GetInstance();
		phoge->SetPos(100, 200);
		std::cout << "hoge-> GetPosX() => " << phoge->GetPosX() << std::endl;
		std::cout << "hoge-> GetPosY() => " << phoge->GetPosY() << std::endl;

		//Foo::CreateInstance(); 
		//{
		//	Hoge* hoo = Foo::GetInstance();
		//	hoo->SetPosZ(100);
		//}
		//Foo::DestroyInstance();
	}
	Hoge::DestroyInstance();	//シングルトンの実態を破棄
}