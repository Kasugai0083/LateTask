# LateTask
後期課題
	以下の内容が含まれたプロジェクトの提出

	・XFileの描画
	・次の関数の自作する
		D3DXMatrixTranslation
		D3DXMatrixScaling
		D3DXMatrixRotationX
		D3DXMatrixRotationY
		D3DXMatrixRotationZ
		D3DXMatrixMultiply
	・ビルボードを描画

	・曲線の描画
		以下の流れを参考に曲線の描画をする

		①．あるオブジェクトの座標を一定フレーム毎に保存する

		②．保存されてる座標と次の座標でベクトルを算出する

		③．②のベクトルに対して直角なベクトルを算出する

		④．③のベクトルを単位ベクトルにする

		⑤．線の幅 / 2 を④のベクトルに掛ける

		⑥．⑤のベクトルに座標を足した新しい座標を作る

		⑦．⑤のベクトルを180度回転する

		⑧．⑦のベクトルと座標を足した新しい座標を作る

		⑨．②～⑧を繰り返してTriangleStripで描画するための頂点の塊を作る

	・スライダー(ゲージ)の作成
		yttm-workのスライダーを参考に右から左と左から右に増加するスライダーを作成する
