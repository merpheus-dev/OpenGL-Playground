namespace LavaMath {
	class Matrix4 {
	public:
		float row1[4];
		float row2[4];
		float row3[4];
		float row4[4];
		
		Matrix4()
		{
			set_to_identity();
		}

		void set_to_identity() {
			for (int i = 0; i < 4; i++) {
				row1[i] = 0;
				row2[i] = 0;
				row3[i] = 0;
				row4[i] = 0;
			}
			row1[0] = 1;
			row2[1] = 1;
			row3[2] = 1;
			row4[3] = 1;
		}
	};

	class Vector3 {
	public:
		float x, y, z;
	};

	//class Operations {
	//	Matrix4 translate(Matrix4 matrix,Vector3 vector)
	//	{

	//		return matrix;
	//	}
	//};

};