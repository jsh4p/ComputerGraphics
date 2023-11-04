#pragma once

#include <string>
#include <memory>
#include <vector>

using namespace std;

class Image {
public:
	Image();
	Image(const int& width, const int& heigth, const int& nChannels);
	Image(const Image& image);
	Image(const string& path);

	Image& operator=(const Image& image);

	vector<int> getPixelColor(const int& col, const int& row) const;
	void setPixelColor(const int& col, const int& row, vector<int> pixelColor);

	bool isRead(const string& path);
	bool isSaved(const string& path);

	~Image();

private:
	int m_width;
	int m_height;
	int m_nChannels;
	int m_size;
	unique_ptr<uint8_t[]> m_data;
	
	static void test();

	friend ostream& operator<<(ostream& out, const Image& image);
	friend class EdgeDetector;
};