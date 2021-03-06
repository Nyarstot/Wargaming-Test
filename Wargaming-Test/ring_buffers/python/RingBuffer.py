class RingBuffer:
    def __init__(self, size: int):
        self.__buffer = [None] * size
        self.__counter = 0
        self.__size = size
        self.__head = 0
        self.__tail = 0

    def push(self, value):
        if self.full():
            raise OverflowError('The buffer is full now')
        self.__buffer[self.__head] = value
        self.__head += 1
        self.__counter += 1
        if self.__head == self.__size:
            self.__head = 0

    def pop(self):
        self.__buffer[self.__tail] = None
        self.__counter -= 1
        self.__tail += 1

    def resize(self, new_size: int):
        temp = RingBuffer(new_size)
        for i in range(self.__size):
            temp[i] = self.__next__()
        self.__buffer = temp.__buffer
        self.__size = temp.__size
        self.__tail = temp.__tail
        self.__head = temp.__head

    def get_from_tail(self):
        return self.__buffer[self.__tail]

    def get_from_head(self):
        return self.__buffer[self.__head]

    def empty(self):
        return self.__counter == 0

    def full(self):
        return self.__counter == self.__size

    def size(self):
        return self.__size

    def get(self):
        return self.__buffer

    @staticmethod
    def __next_index(index: int, size: int):
        return 0 if index == (size - 1) else index + 1

    @staticmethod
    def __prev_index(index: int, size: int):
        return (size - 1) if index == 0 else index - 1

    def __getitem__(self, index: int):
        return self.__buffer[index % self.__size]

    def __setitem__(self, index: int, value):
        self.__buffer[index] = value

    def __iter__(self):
        return self

    def __next__(self):
        value = self.__buffer[self.__tail]
        self.__tail = self.__next_index(self.__tail, self.__size)
        return value