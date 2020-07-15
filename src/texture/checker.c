float checker_texture(float x, float y)
{
	float size = 0.03;
	float col1 = .1;
	float col2 = 0;
	if ((int)(x*1000) % (int)((size * 2)*1000) < (int)(size*1000))
	{
		if ((int)(y * 1000) % (int)((size * 2)*1000) < (int)(size*1000))
		{
			return col1;
		}
		else 
		{
			return col2;
		}
	}	
	else 
	{
		if ((int)(y*1000) % (int)((size * 2)*1000) < (int)(size*1000))
		{
			return col2;
		}
		else 
		{
			return col1;
		}

	}
	return (0);
}
