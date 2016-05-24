# ParticleSystem
* コンピュータグラフィックスのための粒子法プログラムです.

# How to Compile Me
* 必要なもの
 1. C++11コンパイラ
 2. cmake3.0以降
* 依存ライブラリ
 * [FUJI-Math](https://github.com/dearshuto/FUJIMath): 
* コンパイル セッティング. cmakeは大量のファイルを吐き出すので, 作業用ディレクトリを用意しておくことをお勧めします.
 > ~$ cd path/to/ParticleSystem/root   
 > ~$ git submodule update --init //依存ライブラリの取得  
 > ~$ mkdir build //cmakeの作業ディレクトリの作成  
 > ~$ cd build  
 > ~$ cd cmake .. *OS-option*  
y
* ドキュメント
 * Doxyfileが配置されているディレクトリで"doxygen"コマンドを実行してください. docフォルダが作成され, その中にドキュメントが生成されます. index.htmlをブラウザで開いてください

 # How to Use
 * "include/"にヘッダサーチパスを通してください. リンクもお忘れなく. 各クラスについてはドキュメントをご覧ください.
