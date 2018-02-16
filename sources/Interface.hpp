template<class ...Args>
class Constructable {
	PROTECTED virtual void Initialize() = 0;
	PROTECTED virtual void Construct(Args ...args) = 0;
};

class Loadable {
	PUBLIC virtual void Load(const wchar_t* const filePath) = 0;
};
