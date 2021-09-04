// River Information Systems ECE-TRANS-SC3-2006-10r-RIS.pdf
// http://www.unece.org/fileadmin/DAM/trans/doc/finaldocs/sc3/ECE-TRANS-SC3-176e.pdf

#include "ais.h"

namespace mylibais {
	// River Information Systems ECE-TRANS-SC3-2006-10r-RIS.pdf
	Ais8_200_41::Ais8_200_41(const char *nmea_payload, const size_t pad)
		: Ais8(nmea_payload, pad), version(0), country(), section(0), type(0), objectnumber(0), hectometre(0), signal(0), orientation(0), impact(0), 
		light_status(0), spare(0) {

		assert(dac == 200);
		assert(fi == 41);

		//if (!CheckStatus()) {
		//	return;
		//}
		if (num_bits != 168) {
			status = AIS_ERR_BAD_BIT_COUNT;
			return;
		}

		bits.SeekTo(56);
		// version section number             17 bits
		version = bits.ToUnsignedInt(56, 3);

		// country section number             17 bits
		country = bits.ToString(59, 12);
		
		 // Fairway section number             17 bits
		section = bits.ToUnsignedInt(71, 17);

		// Object code                30 bits
		type = bits.ToUnsignedInt(88, 3);

		// Object code                30 bits
		objectnumber = bits.ToUnsignedInt(91, 4);


		// Fairway hectometre                 17 bits
		hectometre = bits.ToUnsignedInt(95, 17);

		// Signal                              1 bits
		signal = bits.ToUnsignedInt(112, 4);

		// Orientation
		orientation = bits.ToUnsignedInt(116, 9);

		// impact
		impact = bits.ToUnsignedInt(125, 3);

		// status
		light_status = bits.ToUnsignedInt(128, 30);

		 // Spare                               2 bits
		spare = bits.ToUnsignedInt(158, 10);
	   
		assert(bits.GetRemaining() == 0);

		status = AIS_OK;

	}

	// ISRS Text
	Ais8_200_44::Ais8_200_44(const char *nmea_payload, const size_t pad)
		: Ais8(nmea_payload, pad) // TODO : add missing fields
	{
	  assert(dac == 200);
	  assert(fi == 44);

	  if (!CheckStatus()) {
		return;
	  }
	 // TODO(schwehr): make this more careful
	  if (num_bits != 200 && (num_bits < 222 || num_bits > 450)) {
		status = AIS_ERR_BAD_BIT_COUNT;
		return;
	  }

	  bits.SeekTo(60);
	  // UN country code                    12 bits
	  country = bits.ToString(60, 12);

	  // Fairway section number             17 bits
	  section = bits.ToString(72, 17);

	  // Object code                30 bits
	  object = bits.ToString(89, 30);

	  // Fairway hectometre                 17 bits
	  hectometre = bits.ToString(119, 17);
  
	  // Spare                               1 bits
	  spare1 = bits.ToUnsignedInt(136, 1);
  
	  // Text 
	  text = bits.ToString(137, 222);
  
	   // Spare                               2 bits
	  spare2 = bits.ToUnsignedInt(359, 2);


	  //assert(bits.GetRemaining() == 0);
	  status = AIS_OK;
	}	

} // namespace mylibais
