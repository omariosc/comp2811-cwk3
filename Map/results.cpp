#include "results.h"

Results::Results(const std::vector<VideoFile *> &videos, Player *player) {
  QScrollArea();

  v = videos;
  p = player;

  // Create label with prompt and set properties for styling
  header = new QLabel("Select country");
  header->setProperty("type", "resultsHeader");
  header->setAlignment(Qt::AlignCenter);
  header->setFixedHeight(30);

  std::vector<VideoFile *> emptyVideos = std::vector<VideoFile *>();
  result = new VideoLibrary(emptyVideos, p);

  QVBoxLayout *l = new QVBoxLayout();

  l->addWidget(header);
  l->addWidget(result);

  l->setMargin(0);

  setLayout(l);
}

void Results::getCountry(QString country) { updateWidget(country); }

void Results::updateWidget(QString country) {
  if (!country.isEmpty()) {
    header->setText("Results from " + country + ":");
  }

  // Randomize video vector
  std::random_device rd;
  auto rng = std::default_random_engine{rd()};
  std::shuffle(std::begin(v), std::end(v), rng);

  auto randomVideos = std::vector<VideoFile *>(v.begin(), v.begin() + 4);

  result->changeVideos(randomVideos);
}
