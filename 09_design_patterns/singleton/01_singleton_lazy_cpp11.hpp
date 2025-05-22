#pragma once
#include <iostream>
#include <mutex>

/**
 * @brief C++11 线程安全懒汉单例模式实现
 *
 * 这是现代C++推荐的单例实现方式，利用局部静态变量的线程安全特性，
 * 避免了传统双重检查锁定模式的复杂性。
 */
class SingletonLazy {
private:
  /**
   * @brief 私有化默认构造函数
   *
   * 防止外部通过new创建实例，确保只有GetInstance()能创建对象。
   * =default表示使用编译器生成的默认实现。
   */
  SingletonLazy() = default;

  /**
   * @brief 私有化析构函数
   *
   * 防止外部直接删除实例，确保生命周期由程序控制。
   */
  ~SingletonLazy() = default;

  /**
   * @brief 删除拷贝构造函数
   *
   * 单例不应被拷贝，删除拷贝构造防止通过拷贝创建新实例。
   */
  SingletonLazy(const SingletonLazy &) = delete;

  /**
   * @brief 删除拷贝赋值运算符
   *
   * 单例不应被赋值，删除拷贝赋值防止通过赋值复制实例。
   */
  SingletonLazy &operator=(const SingletonLazy &) = delete;

public:
  /**
   * @brief 获取单例实例的全局访问点
   *
   * @return SingletonLazy& 返回单例的引用
   *
   * 这是本实现最核心的部分：
   * 1. 使用局部静态变量，C++11保证其初始化是线程安全的
   * 2. 首次调用时构造实例，后续调用直接返回已构造的实例
   * 3. 返回引用避免指针的潜在问题，明确所有权归属
   */
  static SingletonLazy &GetInstance() {
    static SingletonLazy instance; // 线程安全的延迟初始化
    /**
     * static 标识的局部变量存储在程序的静态存储区​（与全局变量相同），而非栈或堆。
     */
    return instance;
  }

  /**
   * @brief 示例成员函数
   *
   * 展示单例的功能接口。
   */
  void Print() { std::cout << "hello" << std::endl; }
};