#include "Color.h"

const shared_ptr<Color> Color::RED = make_shared<Color>(255, 0, 0);
const shared_ptr<Color> Color::GREEN = make_shared<Color>(0, 255, 0);
const shared_ptr<Color> Color::BLUE = make_shared<Color>(0, 0, 255);


double Color::RANDOM_COLORS[7][3]  = {
   {0.0000,    0.4470,    0.7410},
   {0.8500,    0.3250,    0.0980},
   {0.9290,    0.6940,    0.1250},
   {0.4940,    0.1840,    0.5560},
   {0.4660,    0.6740,    0.1880},
   {0.3010,    0.7450,    0.9330},
   {0.6350,    0.0780,    0.1840},
};
