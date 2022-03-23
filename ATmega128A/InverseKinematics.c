#include "Header.H"
double theta1, theta2;
double pre_theta1, pre_theta2;
double C2;
extern char instr[20];

void InverseKinematics (int X, int Y)
{
	C2 = ((double)(pow(X, 2.0) + pow(Y, 2.0) - pow(L1, 2.0) - pow(L2, 2.0))/(double)(2*L1*L2));
	
	if ((C2 < -1) || (C2 > 1))
	{
		sprintf(instr, "FAIL\n");
		Tx_MCUtoPC(instr);
	}
	else if (C2 < 0)
	{
		if ((THETA2_1 < 2.617) && (THETA2_1 > -2.617))
		{
			theta2 = THETA2_1;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %f\n", theta2);
			Tx_MCUtoPC(instr);
		}
		else if ((THETA2_2 < 2.617) && (THETA2_2 > -2.617))
		{
			theta2 = THETA2_2;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %f\n", theta2);
			Tx_MCUtoPC(instr);
		}
		else
		{
			sprintf(instr, "Unavailable Angle");
			Tx_MCUtoPC(instr);
		}
	}
	else if (C2 > 0)
	{
		if (THETA2_3 < 2.617 && THETA2_3 > -2.617)
		{
			theta2 = THETA2_3;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %f\n", theta2);
			Tx_MCUtoPC(instr);
		}
		else if (THETA2_4 < 2.617 && THETA2_4 > -2.617)
		{
			theta2 = THETA2_4;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %f\n", theta2);
			Tx_MCUtoPC(instr);
		}
		else
		{
			sprintf(instr, "Unavailable Angle");
			Tx_MCUtoPC(instr);
		}
	}
	else if (C2 == 0)
	{
		if (pre_theta2 < 0)
		{
			theta2 = -M_PI/2;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %f\n", theta2);
			Tx_MCUtoPC(instr);
		}
		else if (pre_theta2 > 0)
		{
			theta2 = M_PI/2;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %f\n", theta2);
			Tx_MCUtoPC(instr);
		}
	}

	if (THETA1 < 2.094 && THETA1 > -2.094)
	{
			theta1 = -(atan2(Y,X) - atan((L2*sin(theta2))/(L1+L2*C2)));
			sprintf(instr, "theta1 = %lf\n", theta1);
			Tx_MCUtoPC(instr);
	}
	else
	{
		sprintf(instr, "Unavailable Angle");
		Tx_MCUtoPC(instr);
	}
} 