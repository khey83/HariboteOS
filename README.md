# 「30日でできる！OS自作入門」の実践
## 前提環境
 - macOS High Sierra version 10.13.6
## 開発環境準備
1. 適当な作業ディレクトリを作成する
2. tolsetOSXの準備
    1. 以下から`tolsetOSX-070221.dmg`をダウンロード
        - http://shrimp.marokun.net/osakkie/wiki/tolsetOSX/
    2. マウントして`z_tools`ディレクトリを1のディレクトリにコピーする
3. qemuの準備
    1. `brew install qemu`
    2. 以下からmac用のqemuのMakefileをダウンロードする
        - https://github.com/tatsumack/30nichideosjisaku/blob/master/z_tools/qemu/Makefile
    3. `z_tools`ディレクトリ配下に`qemu`ディレクトリを作成してMakefileをその中へ置く
4. バイナリエディタの準備
    1. 以下からダウンロードしてインストール
        - https://ridiculousfish.com/hexfiend/
    - TIPS
        - １列あたりのバイト数を変更するにはウィンドウの幅を調整する
