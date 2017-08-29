#include "recognizer.h"

using namespace tesseract;

Recognizer::Recognizer(QObject *parent) : QObject(parent)
{
    translator = new Translator;
    QObject::connect(this, SIGNAL(translate(char*&)), translator, SLOT(start(char*&)));
    QObject::connect(translator, SIGNAL(showResult(QString)), this, SLOT(showResult(QString)));
}

void Recognizer::start(const QPixmap &img)
{
    char *outText;
    TessBaseAPI *api = new TessBaseAPI();
    QString langDir = QString("%1").arg(qApp->applicationDirPath());

    if (api->Init(langDir.toLatin1().data(), "eng")) {
        qDebug() << "Could not initialize tesseract.\n";
        exit(1);
    }

    QImage qImg = img.toImage();
    Pix *image = qImage2PIX(qImg);
    api->SetImage(image);
    outText = api->GetUTF8Text();

    qDebug() << outText;

    emit translate(outText);

    api->End();
    pixDestroy(&image);
}

void Recognizer::showResult(const QString &result)
{
    emit signalShowResult(result);
}

Pix* Recognizer::qImage2PIX(QImage& qImage) {
  Pix * pixs;
  l_uint32 *lines;

  qImage = qImage.rgbSwapped();
  int width = qImage.width();
  int height = qImage.height();
  int depth = qImage.depth();
  int wpl = qImage.bytesPerLine() / 4;

  pixs = pixCreate(width, height, depth);
  pixSetWpl(pixs, wpl);
  pixSetColormap(pixs, NULL);
  l_uint32 *datas = pixs->data;

  for (int y = 0; y < height; y++) {
    lines = datas + y * wpl;
    QByteArray a((const char*)qImage.scanLine(y), qImage.bytesPerLine());
    for (int j = 0; j < a.size(); j++) {
      *((l_uint8 *)lines + j) = a[j];
    }
  }
  return pixEndianByteSwapNew(pixs);
}
