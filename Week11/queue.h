typedef int element;	// ����� Ÿ��
typedef struct QueueNode {	// ť�� ����� Ÿ�� 
	element item; 
	struct QueueNode *link; 
} QueueNode;
typedef struct {		// ť ADT ����
	QueueNode *front, *rear;
} QueueType;
