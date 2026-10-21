#include "traversal.hpp"
#include <iostream>
#include <system_error>

namespace fs = std::filesystem;

namespace {

void report_error(const fs::path& p, const std::error_code& ec) {
    std::cerr << "my_clt: " << p.string() << ": " << ec.message() << "\n";
}

// Works for both directory_iterator and recursive_directory_iterator,
// because they share the same interface.
template <typename DirIterator>
void collect_entries(const fs::path& root, FileList& result) {
    std::error_code ec;
    DirIterator it(root, fs::directory_options::skip_permission_denied, ec);
    const DirIterator end; // a default-constructed iterator is the "end" sentinel

    if (ec) {
        report_error(root, ec);
        result.had_error = true;
        return;
    }

    while (it != end) {
        // directory_entry::is_regular_file(ec) doesn't throw, and it usually
        // reuses file info the iterator already fetched (no extra system call).
        if (it->is_regular_file(ec)) {
            result.files.push_back(it->path());
        } else if (ec) {
            report_error(it->path(), ec);
            result.had_error = true;
        }

        it.increment(ec); // non-throwing version of ++it
        if (ec) {
            report_error(root, ec);
            result.had_error = true;
            break; // the iterator is no longer usable after a failed increment
        }
    }
}

} // namespace

FileList collect_files(const fs::path& target_path, bool recursive) {
    FileList result;
    std::error_code ec;
    
    // Ask the filesystem about the path once, then make all decisions from that answer.
    const fs::file_status st = fs::status(target_path, ec);

    if (!fs::exists(st)) {
        if (!ec) ec = std::make_error_code(std::errc::no_such_file_or_directory);
        report_error(target_path, ec);
        result.had_error = true;
        return result;
    }

    if (fs::is_regular_file(st)) {
        result.files.push_back(target_path);
    } else if (fs::is_directory(st)) {
        if (recursive) 
            collect_entries<fs::recursive_directory_iterator>(target_path, result);
        else
            collect_entries<fs::directory_iterator>(target_path, result);
    }

    return result;
}