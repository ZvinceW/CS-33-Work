long switch_prob(long x, long n){
	long result = x;
	switch (n){
		/*Fill in code here*/
		case 0x3c:
		case 0x3e:
			result = 0 + x * 8;
			break;
		case 0x3f:
			result = x;
			result >>= 3;
			break;
		case 0x40:
			result = x;
			result <<= 4;
			result -= x;
			x = result;
		case 0x41;
			x *= x;
		default:
			result = x + 0x4b;
	}
	return result;
}