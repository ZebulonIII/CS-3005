void horizontalEdges(PPM& output_image) const
{
	output_image = PPM(height, width);
	output_image.setMaxColorValue(max_color_value);

	for (int i = 1; i < height; i++; i++)
		for (int j = 0; j < width; j++)
		{
			double v2 = linearColometricPixelValue(i, j);
			double v1 = linearCOlometricPixelValue(i - 1, j);
			if (std::abs(v1 - v2) > (max_color_value * 0.1))
				output_image.setPixel(i, j, max_color_value);
			else
				output_image.setPixel(i, j, 0);
		}
}
void verticalEdges(PPM& output_image) const
{
	output_image = PPM(height, width);
	output_image.setMaxColorValue(max_color_value);

	for (int i = 0; i < height; i++)
		for (int j = 1; j < width; j++)
		{
			double v2 = linearColometricPixelValue(i, j);
			double v1 = linearColometricPixelValue(i, j - 1);
			if (std::abs(v1 - v2) > (max_color_value * 0.1))
				output_image.setPixel(i, j, max_color_value);
			else
				output_image.setPixel(i, j, 0);
		}
}
