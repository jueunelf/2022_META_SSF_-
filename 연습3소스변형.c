#define _CRT_OBSOLETE_NO_WARNINGS //�����Լ� ��� ���� ����
#include <stdio.h>
#include <time.h> // delay �Լ� ����� ��� ����

// delay �Լ� ����� 
void delay(clock_t n) {
	clock_t start = clock();
	while (clock()-start<n);
}

int main() {

	//�ڵ��� ���� ������ȣ
	int length_straight = 0;

	//�ڵ��� ���� ������ȣ
	int width_straight = 0;


	//�ڵ��� ���� ��ȸ����ȣ
	int length_left = 0;


	//�ڵ��� ���� ��ȸ����ȣ
	int width_left = 0;

	//������ ���� �Ķ��ҽ�ȣ
	int length_people = 0;

	//������ ���� �Ķ��ҽ�ȣ
	int width_people = 0;

	while (1) {
		printf("�ڵ��� ���� ������ȣ�Դϴ�.\n���κ����� �Ķ����Դϴ�.\n");
		++length_straight;
		delay(5000);//5�� ���� ����(��ǻ� 5�� ���� ��ȣ���� ��������)
		// sleep �Լ� ��� delay �Լ� ��� 

		printf("�ڵ��� ���� ������ȣ�Դϴ�.\n���κ����� �Ķ����Դϴ�.\n");
		++width_straight;
		delay(5000);//������ �� �Ǵ��� ������ ª�� 5�� �� ���̰� ������ 30�ʷ� ������

		printf("�ڵ��� ���� ��ȸ����ȣ�Դϴ�.\n��ü������ �������Դϴ�.\n");
		++length_left;//++������ȣ�� ���߻�Ȳ�� ���� � ��ȣ���� ����ƴ��� Ȯ�ο����� ����Ϸ��� �����س��� ��
		delay(5000);

		printf("�ڵ��� ���� ��ȸ����ȣ�Դϴ�.\n��ü������ �������Դϴ�.\n");
		++width_left;//�����ڽ�ȣ�� �ڵ��� ����, ���ΰ� ��ȸ����ȣ�϶� ��� �������̹Ƿ� ������ �Ǳ� ����� �� ����. �׷��� ++������ �켱 ����.
		delay(5000);

		printf("������������Ƚ��:%d\n������������Ƚ��:%d\n������ȸ������Ƚ��:%d\n������ȸ������Ƚ��:%d\n", length_straight, width_straight, length_left, width_left);		
	}
	return 0;
}
