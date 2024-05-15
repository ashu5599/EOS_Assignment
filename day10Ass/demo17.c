#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MQ_KEY 0x1234

typedef struct msg {
  long type;
  int numbers[2]; // Array to hold two numbers
} msg_t;

int main() {
  int mqid, ret, s;

  // Create message queue
  mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
  if (mqid < 0) {
    perror("msgget() failed");
    _exit(1);
  }

  ret = fork();
  if (ret == 0) {
    // Child process: send two numbers
    msg_t message;
    message.type = 1;

    printf("child: enter two numbers (space separated): ");
    scanf("%d %d", &message.numbers[0], &message.numbers[1]);

    ret = msgsnd(mqid, &message, sizeof(message.numbers), 0);
    if (ret < 0) {
      perror("msgsnd failed");
      _exit(1);
    }

    // Receive the sum from parent
    ret = msgrcv(mqid, &message, sizeof(message.numbers), 2, 0); // Wait for message type 2 (sum)
    if (ret < 0) {
      perror("msgrcv failed");
      _exit(1);
    }

    printf("child: sum received: %d\n", message.numbers[0]); // Print the sum
  } else {
    // Parent process: receive numbers, calculate sum, and send back
    msg_t message;

    printf("parent: waiting for numbers...\n");
    ret = msgrcv(mqid, &message, sizeof(message.numbers), 1, 0); // Wait for message type 1 (numbers)
    if (ret < 0) {
      perror("msgrcv failed");
      _exit(1);
    }

    int sum = message.numbers[0] + message.numbers[1];

    message.type = 2; // Set type to 2 for sum message
    message.numbers[0] = sum; // Store sum in the first element of numbers array

    ret = msgsnd(mqid, &message, sizeof(message.numbers), 0);
    if (ret < 0) {
      perror("msgsnd failed");
      _exit(1);
    }

    // Wait for child process to finish
    wait(&s);
  }

  // Destroy the message queue (uncomment if needed)
  // msgctl(mqid, IPC_RMID, NULL);

  return 0;
}

