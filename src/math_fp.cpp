	// TODO: FIXED POINT MATH
	// TODO: Should these even be used with OpenGL?
	/*
	class Fxp {
		// TODO: case->Case
		public:
		Fxp(float param) {
			value = (long)(param * 65536);
		}

		Fxp(long param) {
			value = param;
		}

		Fxp operator + (Fxp param) {
			return Fxp(value + param.value);
		}

		Fxp operator - (Fxp param) {
			return Fxp(value - param.value);
		}

		Fxp operator * (Fxp param) {
			return Fxp((value * param.value));
		}

		Fxp operator / (Fxp param) {
			return Fxp((value << 16) / param.value);
		}

		short GetUint16() {
			return (unsigned short)(value >> 16);
		}

		float GetFloat() {
			return (((float)value) / 65536);
		}

		short Frac() {
			return (unsigned short) value;
		}

		short Round() {
			// TODO: Does this work on negative numbers?
			if ( short(value) < 0 ) {
				// if left fractional bit 1
				return short(value >> 16) + 1;
			}
			else {
				return short(value >> 16);
			}
		}
		// private:
		long value;
		// short most, less
	};
	*/
	/* USAGE:
		fxp value1 = 2.4f;
		fxp value2 = 2.4f;
		fxp value3 = value1 * value2;
		float value4 = value3.GetFloatingPoint();
	*/

	//void generate_sin_table();
