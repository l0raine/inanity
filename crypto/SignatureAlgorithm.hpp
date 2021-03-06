#ifndef ___INANITY_CRYPTO_SIGNATURE_ALGORITHM_HPP___
#define ___INANITY_CRYPTO_SIGNATURE_ALGORITHM_HPP___

#include "crypto.hpp"

BEGIN_INANITY

class File;

END_INANITY

BEGIN_INANITY_CRYPTO

class RandomAlgorithm;

/// Абстрактный класс алгоритма цифровой подписи.
/** Позволяет генерировать пары ключей, подписывать ими данные,
и проверять подписи. Работа с данными реализована не как с потоками,
а просто, по указателям, так как, во-первых, размер данных
фиксирован, а во-вторых, предполагается, что данные небольшие,
то есть дайджесты от настоящих данных.
*/
class SignatureAlgorithm : public Object
{
public:
	/// Получить размер входных данных.
	virtual size_t GetDataSize() const = 0;
	/// Получить размер открытого ключа цифровой подписи.
	virtual size_t GetPublicKeySize() const = 0;
	/// Получить размер закрытого ключа цифровой подписи.
	virtual size_t GetPrivateKeySize() const = 0;
	/// Получить размер цифровой подписи.
	virtual size_t GetSignatureSize() const = 0;

	/// Сгенерировать пару ключей, используя заданный генератор случайных чисел.
	virtual void GenerateKeyPair(ptr<RandomAlgorithm> randomAlgorithm, void* privateKey, void* publicKey) = 0;
	/// Подписать данные.
	virtual void Sign(const void* data, const void* privateKey, void* signature) = 0;
	/// Проверить данные.
	virtual bool Verify(const void* data, const void* publicKey, const void* signature) = 0;
};

END_INANITY_CRYPTO

#endif
