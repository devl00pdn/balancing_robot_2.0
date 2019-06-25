/*
 * statistic_data_producer.h
 *
 *  Created on: Dec 5, 2018
 *      Author: demid
 *
 *      Назначеие :
 *      Позволяет получать уникальную структуру данных класса наследника путём полиморизма, БЕЗ получения доступа к остальным
 *      публичным методам класса. Вычитка происходит всегда из одного виртуального метода.
 */

#ifndef DATA_GENERATOR_H_
#define DATA_GENERATOR_H_

class Data_generator{
 public:

    struct data_base_t{
        virtual ~data_base_t(){
        }
    };

    virtual bool get_data(data_base_t *d) = 0;
};

// Преднаязначен для хранения структур данных
// и источников из которых будет составлен кадр телеметрии
class Updater_base{
public:
    struct source{
        Data_generator::data_base_t *data; // ссылка на структуру которую хотим обновть
        Data_generator *generator; // обект который может обновить эту структуру
    };
    // Для инциализации нужно передать указалети на обекты унаследованные от  Analytics_data_generator и
    // ссылка на объект структуры унаследованной от  Analytics_data_generator::data_base_t. Всё это пердаётся в формате массива структур
    template <int N>
    Updater_base(const source (&sources_)[N]):sources_array_cell_num(N), sources(sources_) {}
    Updater_base() = delete;
    ~Updater_base(){}
    bool update_(){
        bool rv = true;
        if(!sources){
            return false;
        }
        if(!sources_array_cell_num){
            return false; // Массив sources не содержит элементов
        }
        for(int i = 0; i < sources_array_cell_num; ++i){
            if(!sources[i].generator->get_data(sources[i].data)){
                rv = false; // хотябы один из источников не смог обновить исходную структуры данных
            }
        }
        return rv;
    }
    const int sources_array_cell_num = 0;
    const source *sources = nullptr;
};


// Пример реализации класса из которого необходимо вычитать уникальную структуру

/*

class Statistic_1: public Statistic_data_generator{
public:

    // Уникальная структура данных 1 для вычитки
    struct data_1_t : public Statistic_data_generator::data_base_t{
         ~data_1_t(){}
        int a;
        int b;
        int c;
    };

    // Уникальная структура данных 2 для вычитки
    struct data_2_t : public Statistic_data_generator::data_base_t{
         ~data_1_t(){}
        float a;
        int b;
        uint8_t c;
    };

    Statistic_1(){}
    ~Statistic_1(){}

    // Метод к которому не хочется предоставлять доступ всем подряд
    void self_desturction(){
    }

    // Реадизация вирутального методо для вычитки двух разных структур
    bool get_data(Statistic_data_generator::data_base_t *d){
        if(!d){
            return false;
        }

        data_1_t* data1_ptr = dynamic_cast<data_1_t*>(d);
        data_2_t* data2_ptr = dynamic_cast<data_2_t*>(d);

        if(data1_ptr){
            mutex.lock();
            *data1_ptr = this->stat1;
            mutex.unlock();
            return true;
        }
        if(data2_ptr){
            mutex.lock();
            *data2_ptr = this->stat2;
            mutex.unlock();
            return true;
        }

        return false;
    }

private:
    data_1_t stat1;
    data_2_t stat2;
};

 */

#endif /* DATA_GENERATOR_H_ */
