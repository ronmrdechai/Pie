namespace pie {

template <typename... Args>
python_object::python_object(Args&&... args) :
    python_object(parse_object(std::forward<Args>(args)...)) { }

} // namespace pie
