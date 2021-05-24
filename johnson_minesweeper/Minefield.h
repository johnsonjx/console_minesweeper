#pragma once

class Minefield
{
public:
	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Revealed
		};
	private:
		char tileValue;
		char highlightedValue;
		char flaggedValue;
		int revealedValue;
		State state;
	public:
		Tile()
		{
			tileValue = 'x';
			highlightedValue = 'H';
			flaggedValue = 'B';
			revealedValue = 0;
			state = Minefield::Tile::State::Hidden;
		}
		inline bool GetHasBomb() const { return bHasBomb; }
		inline void SetHasBomb(bool hasBomb) { bHasBomb = hasBomb; }

		char GetTileValue() { return tileValue; }
		void SetTileValue(char val) { tileValue = val; }

		char GetHighlightedValue() { return highlightedValue; }
		void SetHighlightedValue(char val) { highlightedValue = val; }

		char GetFlaggedValue() { return flaggedValue; }
		void SetFlaggedValue(char val) { flaggedValue = val; }

		int GetRevealedValue() { return revealedValue; }
		void SetRevealedValue(int val) { revealedValue = val; }

		State GetState() { return state; }
		void SetState(State tileState) { state = tileState; }

	private:
		bool bHasBomb = false;
	};
};