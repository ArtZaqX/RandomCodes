class Transition
{
    // Index of vertex which connects with this.
    public int VertexIndex;

    // Alphabet/Regex which is accepted.
    public string TransitionString;

    public static bool operator ==(Transition Obj1, Transition Obj2)
    {
        return Obj1.VertexIndex == Obj2.VertexIndex && (Obj1.TransitionString.CompareTo(Obj2.TransitionString) == 0);
    }

    public static bool operator !=(Transition Obj1, Transition Obj2)
    {
        return !(Obj1.VertexIndex == Obj2.VertexIndex);
    }
}


class State
{
    // Index of this State.
    readonly int Index;

    // Fields for determining the state's status in the machine.
    public bool IsInitial;
    public bool IsFinal;
    public bool IsDead;

    // Data of all states connected to this.
    // Each element of the list contains an index of the 
    // connecting state and the accepted regex to that state.
    public LinkedList<Transition> Transitions;

    // Constructor
    public State(int InIndex)
    {
        Transitions = new LinkedList<Transition>();

        IsFinal = false;
        IsInitial = false;
        IsDead = false;

        Index = InIndex;
    }

    public void AddTransition(int IndexB, string InRegex)
    {
        Transition Temp = new Transition();
        Temp.VertexIndex = IndexB;
        Temp.TransitionString = InRegex;

        // Traverse through the whole list to see if the given transition already exists.
        foreach (Transition Element in Transitions)
            if (Element == Temp)
                return;     // Transition already exists, abort.

        // Transition does not exist.
        Transitions.AddLast(Temp);

    }

    // Searches all transitions to match the given regex.
    // Returns the index of the state if the match is found, else returns -1.
    public int GetNextStateIndex(string InputRegex)
    {
        foreach (Transition Element in Transitions)
        {
            if (Element.TransitionString.CompareTo(InputRegex) == 0)
                return Element.VertexIndex;
        }
        return -1;
    }
}

class Machine
{
    // Fields for implementation of the Machine (graph).
    readonly State[] Vertices;
    readonly int MachineSize;

    // The index of the state at which the machine is after 
    // accepting the most recent input.
    int CurrentStateIndex;


    // Constructor
    public Machine(int InSize)
    {
        MachineSize = InSize;

        // Initialize the array of vertices.
        Vertices = new State[MachineSize];
        for (int Index = 0; Index < MachineSize; Index++)
            Vertices[Index] = new State(Index);

    }

    public void AddTransition(int IndexA, int IndexB, string Regex)
    {
        Vertices[IndexA].AddTransition(IndexB, Regex);
    }

    public void SetInitialState(int Index)
    {
        CurrentStateIndex = Index;
        Vertices[Index].IsInitial = true;
    }

    public void SetFinalState(int Index)
    {
        Vertices[Index].IsFinal = true;
    }

    public void SetDeadState(int Index)
    {
        Vertices[Index].IsDead = true;
    }

    // Returns the status of input Regex.
    public string Transition(string InputRegex)
    {
        int Temp = Vertices[CurrentStateIndex].GetNextStateIndex(InputRegex);
        if (Temp > -1)
        {
            string ReturnStatus = "";
            if (CurrentStateIndex == Temp)
                ReturnStatus = "Self Transitioned.\n";
            CurrentStateIndex = Temp;
            if (Vertices[CurrentStateIndex].IsDead)
                ReturnStatus += "Dead state reached. String does not exist in L.\n";
            if (Vertices[CurrentStateIndex].IsFinal)
                ReturnStatus += "Final state reached. String exists in L.\n";
            ReturnStatus += "Transitioned to " + CurrentStateIndex + ".";
            return ReturnStatus;
        }
        else
            return "No transition exists.";
    }
}
