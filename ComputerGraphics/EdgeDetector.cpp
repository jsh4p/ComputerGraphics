#include "EdgeDetector.h"
#include <stdexcept>

Image EdgeDetector::ApplyMask(const Image& image, const m_nx& mask) {
	if (image.m_nChannels != 1) {
		throw runtime_error("Изображение должно быть в градациях серого\n");
	}

	Image newImage = image;
	vector<vector<int>> data(mask.size(), vector<int>(image.m_width * image.m_height, 0));

	for (int n = 0; n < mask.size(); ++n) {
		for (int y = mask[n].size() / 2; y < image.m_height - mask[n].size() / 2; ++y) {
			for (int x = mask[n].size() / 2; x < image.m_width - mask[n].size() / 2; ++x) {
				int newPixel = 0;

				for (int i = 0; i < mask[n].size(); ++i) {
					for (int j = 0; j < mask[n].size(); ++j) {
						newPixel += mask[n][i][j] * image.m_data[(y - mask[n].size() / 2 + i)
							* image.m_width + x - mask[n].size() / 2 + j];
					}
				}

				data[n][y * image.m_width + x] = newPixel;
			}
		}
	}

	for (int y = 0; y < image.m_height; ++y) {
		for (int x = 0; x < image.m_width; ++x) {
			int sum = 0;

			for (int n = 0; n < mask.size(); ++n) {
				sum += pow(data[n][y * image.m_width + x], 2);
			}

			data[0][y * image.m_width + x] = round(sqrt(sum));
		}
	}

	for (int y = mask[0].size() / 2; y < image.m_height - mask[0].size() / 2; ++y) {
		for (int x = mask[0].size() / 2; x < image.m_width - mask[0].size() / 2; ++x) {
			newImage.m_data[y * image.m_width + x] = max(0, min(data[0][y * image.m_width + x], 255));
		}
	}

	return newImage;
}

Image EdgeDetector::LaplaceOperator(const Image& image) {
	return ApplyMask(image, LaplaceMask);
}

Image EdgeDetector::RobertsOperator(const Image& image) {
	return ApplyMask(image, RobertsMask);
}

Image EdgeDetector::SobelOperator(const Image& image) {
	return ApplyMask(image, SobelMask);
}

//int minElem = *min_element(data.begin(), data.end()); // нормализация яркости
//
//if (minElem < 0) {
//	for (int i = 0; i < m_width * m_height; ++i) {
//		data[i] -= minElem;
//	}
//}

//int maxElem = *max_element(data.begin(), data.end());

//if (maxElem > 255) {
//	for (int i = 0; i < m_width * m_height; ++i) {
//		data[i] = round(data[i] * 255.0 / maxElem);
//	}
//}

//for (int i = 0; i < m_width * m_height; ++i) {
//	newImage.m_data[i] = data[i];
//}