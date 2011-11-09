#ifndef ___INANITY_STREAM_READER_HPP___
#define ___INANITY_STREAM_READER_HPP___

#include "String.hpp"

BEGIN_INANITY

class InputStream;

/// Класс читателя из потока ввода.
/** По сути является просто вспомогательным объектом. Предоставляет
сервис чтения из потока ввода бинарных простых типов данных.
*/
class StreamReader : public Object
{
private:
	ptr<InputStream> stream;
	size_t read;

public:
	/// Создать читатель.
	/**
	\param stream Поток ввода.
	*/
	StreamReader(ptr<InputStream> stream);

	/// Получить значение счётчика считываемых данных.
	size_t GetReadSize() const;

	/// Прочитать произвольные данные.
	void Read(void* data, size_t size);

	/// Прочитать простое данное из потока ввода.
	/**
	\tparam T Тип простого данного.
	\return Считанное данное.
	*/
	template <typename T>
	T Read()
	{
		T data;
		Read(&data, sizeof(data));
		return data;
	}

	/// Считать строку из потока ввода
	String ReadString();

	/// Считать сокращенное число.
	/** Сокращенные числа записываются в особом формате (см. примечания к реализации),
	что обеспечивает сокращенный размер записи. */
	size_t ReadShortly();

	/// Пропустить 0 или более байт, чтобы достичь необходимого выравнивания.
	/** Выравнивание должно быть степенью двойки!
	Сами байты не считываются. */
	void ReadGap(size_t alignment);
};

END_INANITY

#endif
