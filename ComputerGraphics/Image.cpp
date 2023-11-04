#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Image.h"
#include <iostream>
#include "stb_image.h"
#include "stb_image_write.h"
#include <stdexcept>

Image::Image() {
	m_height = 0;
	m_width = 0;
	m_size = 0;
	m_nChannels = 0;
	m_data = nullptr;
}

Image::Image(const int& width, const int& heigth, const int& nChannels) {
	m_width = width;
	m_height = heigth;
	m_nChannels = nChannels;
	m_size = m_width * m_height * m_nChannels;
	
	m_data = make_unique<uint8_t[]>(m_size);
	for (int i = 0; i < m_size; ++i) {
		m_data[i] = 0;
	}
}

Image::Image(const Image& image) {
	m_width = image.m_width;
	m_height = image.m_height;
	m_nChannels = image.m_nChannels;
	m_size = image.m_size;
	
	m_data = make_unique<uint8_t[]>(m_size);
	for (int i = 0; i < m_size; ++i) {
		m_data[i] = image.m_data[i];
	}
}

Image::Image(const string& path) : Image() {
	if (!isRead(path)) {
		throw runtime_error("Ошибка при чтении фотографии\n");
	}
}

Image& Image::operator=(const Image& image) {
	if (this == &image) {
		return *this;
	}

	m_width = image.m_width;
	m_height = image.m_height;
	m_nChannels = image.m_nChannels;
	m_size = image.m_size;

	m_data = make_unique<uint8_t[]>(m_size);
	for (int i = 0; i < m_size; ++i) {
		m_data[i] = image.m_data[i];
	}

	return *this;
}

vector<int> Image::getPixelColor(const int& col, const int& row) const {
	vector<int> pixelColor(m_nChannels);

	int ind = (row * m_width + col) * m_nChannels;

	for (int i = 0; i < m_nChannels; ++i) {
		pixelColor[i] = m_data[ind + i];
	}

	return pixelColor;
}

void Image::setPixelColor(const int& col, const int& row, vector<int> pixelColor) {
	if (m_nChannels != pixelColor.size()) {
		throw runtime_error("Размер вектора не соответствует количеству каналов\n");

		return;
	}
	
	int ind = (row * m_width + col) * m_nChannels;

	for (int i = 0; i < m_nChannels; ++i) {
		 m_data[ind + i] = pixelColor[i];
	}
}

bool Image::isRead(const string& path) {
	try {
		m_data.reset(stbi_load(path.c_str(), &m_width, &m_height, &m_nChannels, 0));
		if (m_data) {
			m_size = m_width * m_height * m_nChannels;
		}

		return true;
	} catch (const exception& ex) {
		cerr << ex.what() << endl;

		return false;
	}
}

bool Image::isSaved(const string& path) {
	return stbi_write_png(path.c_str(), m_width, m_height, m_nChannels, m_data.get(), 0);
}

void Image::test() {
	Image test("test.png");

	int newWidth = test.m_width * 2;
	int newHeight = test.m_height * 2;
	int newSize = newWidth * newHeight * test.m_nChannels;
	Image newImage(newWidth, newHeight, test.m_nChannels);

	for (int i = 0; i < newSize; i += test.m_nChannels) {
			newImage.m_data[i] = 255;
			if (test.m_nChannels == 4) {
				newImage.m_data[i + 3] = 255;
			}
	}

	int dx = (newWidth - test.m_width) / 2;
	int dy = (newHeight - test.m_height) / 2;
	
	for (int y = dy; y < dy + test.m_height; ++y) {
		for (int x = dx; x < dx + test.m_width; ++x) {
			vector<int> pixelColor = test.getPixelColor(x - dx, y - dy);
			newImage.setPixelColor(x, y, pixelColor);
		}
	}

	newImage.isSaved("test_result.png");
}

ostream& operator<<(ostream& out, const Image& image) {
	for (int i = 0; i < image.m_size; ++i) {
		if (i % image.m_nChannels == 0) {
			out << endl;
		}
		out << (int) image.m_data[i] << " ";
	}

	return out;
}

Image::~Image() = default;
