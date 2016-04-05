# ParticleSystem
by Shuto Shikama

* 粒子を利用したシミュレーションプログラム

# How to Compile Me
* 必要なもの
 1. C++11コンパイラ
 2. cmake3.0以降
* 依存ライブラリ
 * [FUJI-Math](git@git.fj.ics.keio.ac.jp:shikama/FUJI-Math.git): 自作数学ライブラリ
* コンパイル セッティング
 > ~$ cd path/to/ParticleSystem/root   
 > ~$ git submodule update --init //依存ライブラリの取得  
 > ~$ mkdir build //cmakeの作業ディレクトリの作成  
 > ~$ cd build  
 > ~$ cd cmake .. *OS-option*  
