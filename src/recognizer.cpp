#include "recognizer.h"

using namespace tesseract;

Recognizer::Recognizer(QObject *parent) : QObject(parent)
{

}

void Recognizer::start(const QPixmap &img)
{
    char *outText;
    TessBaseAPI *api = new TessBaseAPI();

    QString langDir = qApp->applicationDirPath();
    QString translateFrom = Language::getShortName(App::theApp()->settings()->value("/Settings/Languages/from", "Auto").toString());

    // if auto is selected - create a language string in format: "shortname+shortname+shortname...etc"
    if (translateFrom == "auto") {
        translateFrom = "";
        foreach (Lang language, Language::languages) {
            if (language.name == "Auto") continue;
            translateFrom += language.shortName + "+";
        }

        // remove the last "+" char
        translateFrom.chop(1);
    }

    if (api->Init(langDir.toLatin1().data(), translateFrom.toLatin1().data())) {
        qDebug() << "Could not initialize tesseract.\n";
        exit(1);
    }

    QImage qImg = img.toImage();
    Pix *image = qImage2PIX(qImg);
    api->SetImage(image);
    outText = api->GetUTF8Text();

    emit recognized(QString(outText));

    api->End();
    pixDestroy(&image);
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
