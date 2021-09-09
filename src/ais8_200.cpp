// River Information Systems ECE-TRANS-SC3-2006-10r-RIS.pdf
// http://www.unece.org/fileadmin/DAM/trans/doc/finaldocs/sc3/ECE-TRANS-SC3-176e.pdf

#include "ais.h"

namespace mylibais {
	// River Information Systems ECE-TRANS-SC3-2006-10r-RIS.pdf
	//
	Ais8_200_41::Ais8_200_41(const char *nmea_payload, const size_t pad)
		: Ais8(nmea_payload, pad), version(0), country(), section(0), objectType(0), objectNumber(0), hectometre(0), signalForm(0), orientation(0), impact(0), 
		lightStatus(0), spare(0) {

		assert(dac == 200);
		assert(fi == 41);

		//if (!CheckStatus()) {
		//	return;
		//}
		//if (num_bits != 168) {
		//	status = AIS_ERR_BAD_BIT_COUNT;
		//	return;
		//}

		bits.SeekTo(56);
		// version section number             17 bits
		version = bits.ToUnsignedInt(56, 3);

		// country section number             17 bits
		country = bits.ToString(59, 12);
		
		 // Fairway section number             17 bits
		section = bits.ToUnsignedInt(71, 17);

		// Object code                30 bits
		objectType = bits.ToUnsignedInt(88, 3);

		// Object code                30 bits
		objectNumber = bits.ToUnsignedInt(91, 4);

		// Fairway hectometre                 17 bits
		hectometre = bits.ToUnsignedInt(95, 17);

		// Signal                              1 bits
		signalForm = bits.ToUnsignedInt(112, 4);

		// Orientation
		orientation = bits.ToUnsignedInt(116, 9);

		// impact
		impact = bits.ToUnsignedInt(125, 3);

		// status
		lightStatus = bits.ToUnsignedInt(128, 30);

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

	Ais8_200_25::Ais8_200_25(const char *nmea_payload, const size_t pad)
		: Ais8(nmea_payload, pad), version(0), country(), sectionNumber(0), objectCode(), bridgeClearance(0),minutesOfDay(0), accuracy(0), spare(0) {

		assert(dac == 200);
		assert(fi == 25);

		//if (!CheckStatus()) {
		//	return;
		//}
		if (num_bits != 168) {
			status = AIS_ERR_BAD_BIT_COUNT;
			return;
		}

		bits.SeekTo(56);
		// version section number             3 bits
		version = bits.ToUnsignedInt(56, 3);

		// Country code          12 bits
		country = bits.ToString(59, 12);
		
		 // Fairway section number             17 bits
		sectionNumber = bits.ToUnsignedInt(71, 17);

		// Object code                30 bits
		objectCode = bits.ToString(88, 30);

		// Fairway hectometre                 17 bits
		hectometre = bits.ToUnsignedInt(118, 17);

		//bridge clearance                             14 bits
		bridgeClearance = bits.ToUnsignedInt(135, 14);

		// Minutes of the day 11 bits
		minutesOfDay = bits.ToUnsignedInt(149, 11);

		// Accuracy 5 bits
		accuracy = bits.ToUnsignedInt(160, 5);

		 // Spare                               3 bits
		spare = bits.ToUnsignedInt(165, 3);
	   
		//assert(bits.GetRemaining() == 0);

		status = AIS_OK;

	}

    // ISRS Water Level
	Ais8_200_26::Ais8_200_26(const char *nmea_payload, const size_t pad)
		: Ais8(nmea_payload, pad) // TODO : add missing fields
	{
	  assert(dac == 200);
	  assert(fi == 26);

	  if (!CheckStatus()) {
		return;
	  }

	  if (num_bits != 168) {
		status = AIS_ERR_BAD_BIT_COUNT;
		return;
	  }

	  bits.SeekTo(56);
		// version 3 bits
		version = bits.ToUnsignedInt(56, 3);

	  // country code             12 bits
      country = bits.ToString(59, 12);

	  // Gauge ID             11 bits
	  gaugeID_1 = bits.ToUnsignedInt(71, 11);

	  // Water Level Ref                3 bits
	  waterLevelRef_1 = bits.ToUnsignedInt(82, 3);

	  // Water Level Value                17 bits
	  waterLevelValue_1 = bits.ToUnsignedInt(85, 17);

	  // Gauge ID             11 bits
	  gaugeID_2 = bits.ToUnsignedInt(102, 11);

	  // Water Level Ref                3 bits
	  waterLevelRef_2 = bits.ToUnsignedInt(113, 3);

	  // Water Level Value                17 bits
	  waterLevelValue_2 = bits.ToUnsignedInt(116, 17);

	  // Gauge ID             11 bits
	  gaugeID_3 = bits.ToUnsignedInt(133, 11);

	  // Water Level Ref                3 bits
	  waterLevelRef_3 = bits.ToUnsignedInt(144, 3);

	  // Water Level Value                17 bits
	  waterLevelValue_3 = bits.ToUnsignedInt(147, 17);
  
	  // Spare                               1 bits
	  spare = bits.ToUnsignedInt(164, 4);
  
	  //assert(bits.GetRemaining() == 0);
	  status = AIS_OK;
	}	

} // namespace mylibais
