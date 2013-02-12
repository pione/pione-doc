pione-doc
=========

pione-doc はPIONEに関するドキュメント及びその生成機能をまとめたものです。

## Documentations

* マニュアル(manual)
* 初めの一歩(get started)
* チュートリアル(tutorial)

## ドキュメントの生成方法

### 1. review のインストール

最初にreview(出版システム)をインストールします。

    gem install review

もしくは

    git clone git://github.com/kmuto/review.git

にてreviewを取得して下さい。

### 2. rake

HTMLファイルを生成する場合：

    rake manula:ja:html

PDFファイルを生成する場合：

    rake manual:ja:pdf

他のドキュメントの生成については、下記でrakeタスクを確認して下さい。

    rake -T

## 貢献

どなたかドキュメントを書くのを手伝って頂けると大変助かります。
誤字等の指摘よろしくお願いします。

## License

pione-doc 及びその生成されたドキュメントは、PIONEプロジェクトに属するものとして、
MITライセンスに従い再配布・修正出来ます。
