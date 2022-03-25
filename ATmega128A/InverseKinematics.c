#include "Header.H"

double theta1, theta2;                      // 첫 번째 모터와 두 번째 모터에 입력할 각도
double pre_theta1, pre_theta2;              // 이전에 모터에 입력된 각도
double C2;                                  // cos(theta2)
extern char instr[20];                      // PC로 DATA를 송신

void InverseKinematics (int X, int Y)               // 매개변수로 좌표를 받아 두 모터가 회전해야할 각도를 계산   (따로 설명을 올릴 예정)
{
	C2 = ((double)(pow(X, 2.0) + pow(Y, 2.0) - pow(L1, 2.0) - pow(L2, 2.0))/(double)(2*L1*L2));        // MATLAB에서 계산한 cos(theta2) 수식
	
	if ((C2 < -1) || (C2 > 1))                      
	{
		sprintf(instr, "FAIL\n");
		Tx_MCUtoPC(instr);
	}
	else if (C2 < 0)								             
	{
		if ((THETA2_1 < 0.0006 && THETA2_1 > 0) || (THETA2_1 > -0.0006 && THETA2_1 < 0))
		{
			theta2 = 0;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %lf\n", theta1);
			Tx_MCUtoPC(instr);
		}
	    else if ((THETA2_1 < 2.617) && (THETA2_1 > -2.617))
		{
			theta2 = THETA2_1;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %f\n", theta2);
			Tx_MCUtoPC(instr);
		}
		else if ((THETA2_2 < 0.0006 && THETA2_2 > 0) || (THETA2_2 > -0.0006 && THETA2_2 < 0))
		{
			theta2 = 0;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %lf\n", theta1);
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
		if ((THETA2_3 < 0.0006 && THETA2_3 > 0) || (THETA2_3 > -0.0006 && THETA2_3 < 0))
		{
			theta2 = 0;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %lf\n", theta1);
			Tx_MCUtoPC(instr);
		}
		else if (THETA2_3 < 2.617 && THETA2_3 > -2.617)
		{
			theta2 = THETA2_3;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %f\n", theta2);
			Tx_MCUtoPC(instr);
		}
		else if ((THETA2_4 < 0.0006 && THETA2_4 > 0) || (THETA2_4 > -0.0006 && THETA2_4 < 0))
		{
			theta2 = 0;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %lf\n", theta1);
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
		if (pre_theta2 < 0)                  // 이전 theta2가 0보다 작은 경우, -90도가 더 가까움
		{
			theta2 = -M_PI/2;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %f\n", theta2);
			Tx_MCUtoPC(instr);
		}
		else if (pre_theta2 > 0)            // 이전 theta2가 0보다 큰 경우, 90도가 더 가까움
		{
			theta2 = M_PI/2;
			pre_theta2 = theta2;
			sprintf(instr, "theta2 = %f\n", theta2);
			Tx_MCUtoPC(instr);
		}
	}

	if ((THETA1 < 0.0006 && THETA1 > 0) || (THETA1 > -0.0006 && THETA1 < 0))
	{
		theta1 = 0;
		sprintf(instr, "theta1 = %lf\n", theta1);
		Tx_MCUtoPC(instr);
	}
	
	else if (THETA1 < 2.094 && THETA1 > -2.094)
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