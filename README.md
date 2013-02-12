pione-doc
=========

pione-doc is a set of documentations and its generation tasks for PIONE.

## Documentations

* manual
* get started
* tutorial

## How-to generate documents

### 1. install review

First, you need to install review(publishing tool).

    gem install review

or

    git clone git://github.com/kmuto/review.git

### 2. rake

If you want to generate HTML files,

    rake manula:ja:html

If you want to generate PDF,

    rake manual:ja:pdf

And you want to generate others, see rake's task list.

    rake -T

## Contribute

Please contribute!

## License

You can distribute and modify pione-doc and the generated documents
under MIT license(same as PIONE's license).

