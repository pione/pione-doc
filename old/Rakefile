
def clean_dir(dir)
  remove_entry_secure(dir) if File.exist?(dir)
  mkdir_p(dir)
end

OUTPUT = {
  :manual_ja_html => 'manual-html/ja/',
  :manual_ja_pdf => 'manual-pdf/ja/'
}

PIONE_DOC_HOME = File.dirname(__FILE__)

desc "Update CSS files"
task "update-css" do
  cp_r 'css', OUTPUT[:manual_ja_html]
end

desc 'Generate manual in all formats'
task 'manual' => [
  'manual:ja:html',
  'manual:ja:pdf'
]

desc 'Generate manual in HTML format'
task 'manual:ja:html' do
  path = OUTPUT[:manual_ja_html]
  # clean up the output directory
  clean_dir(path)
  # copy css files
  cp_r 'css', path
  # make index
  cd 'manual/ja' do
    sh 'review-index --html -a > index.html'
  end
  mv 'manual/ja/index.html', path
  # make manual pages
  cd path do
    opts = '--target=html --stylesheet=css/base.css --htmlversion=5'
    dir = '--directory=%s' % File.join(PIONE_DOC_HOME, 'manual', 'ja')
    sh 'review-compile %s %s' % [opts, dir]
  end
end

desc "Genereate manual in PDF format"
task 'manual:ja:pdf' do
  path = OUTPUT[:manual_ja_pdf]
  # clean up the output directory
  clean_dir(path)
  # make pdf
  cd 'manual/ja' do
    sh 'review-pdfmaker config.yml'
  end
  mv 'manual/ja/pione-manual-ja.pdf', path
end

