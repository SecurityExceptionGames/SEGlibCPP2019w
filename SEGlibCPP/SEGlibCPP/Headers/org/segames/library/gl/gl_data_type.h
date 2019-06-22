#pragma once

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				An enum for different types of data, ie. what it represents, used in OpenGL.

				* @author	Philip Rosberg
				* @since	2019-06-10
				* @edited	2019-06-10
			*/
			enum GLDataType
			{
				VERTEX = 0,
				NORMAL = 1,
				COLOR = 2,
				TEX_COORD = 3,
				EDGE_FLAG = 4,
				INDEX = 5,
				ATTRIBUTE = 6
			};

		}

	}

}