from queue import Queue

class AIQueues:
    def __init__(self, queueSize : int = 10):
        """
        Constructor of the AI Queue Class
        Init two queues, one corresponding to the API queue, the second one to have an infinite stock of object
        The Queue's object will be function pointer
        When a "Ask..." function is send to the Api, please put the "Get..." corresponding in the Queue with addInAiQueue()
        """
        self.__serverQueue : Queue = Queue(queueSize)
        self.__aiQueue : Queue = Queue(-1)

    def isServerQueueFull(self) -> bool:
        """ If the server Queue cannot accept any more object, return True """
        return self.__serverQueue.full()

    def isServerQueueEmpty(self) -> bool:
        """ If the server Queue hasn't any object, return True """
        return self.__serverQueue.empty()

    def addInAiQueue(self, newObj, transferToServerQueue : bool = False):
        """
        Add the newObj in the infinite Queue
        if transferToServerQueue is True, it will try to put directly in the server Queue (Use case : Begin of the AI)
        """
        if transferToServerQueue and not self.isServerQueueFull():
            self.__addInServerQueue(newObj)
        else:
            self.__aiQueue.put(newObj)

    def __popFromAiQueue(self):
        """ Return the front element of the infinite Queue """
        return self.__aiQueue.get()

    def __addInServerQueue(self, newObj) -> None:
        """
        Add the newObj in the server Queue
        BEWARE : Check if the server Queue isn't full before calling this function
        """
        self.__serverQueue.put(newObj)

    def __popFromServerQueue(self):
        """ Return the front element of the server Queue """
        return self.__serverQueue.get()

    def addInServerQueue(self) -> int:
        """
        Empty the infinite Queue until the server Queue is full
        Return the number of objects transfered
        """
        added : int = 0
        while not self.isServerQueueFull():
            newObj = self.__popFromAiQueue()
            self.__addInServerQueue(newObj)
            added += 1
        return added

    def emptyServerQueue(self, nbToEmpty : int = 1):
        """
        Empty the server Queue of nbToEmpty (min 1 max 10) while the serverQueue isn't empty
        Return the poped objects in a list
        """
        objGetter = []
        while not self.isServerQueueEmpty() and nbToEmpty > 0:
            newObj = self.__popFromServerQueue()
            objGetter.append(newObj)
            nbToEmpty -= 1
        return objGetter