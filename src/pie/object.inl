namespace pie {

template <typename... Args>
object::object(Args&&... args) :
    object(parse_object(std::forward<Args>(args)...)) { }

} // namespace pie
