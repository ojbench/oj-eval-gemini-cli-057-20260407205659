#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Student {
    string id;
    string name;
    int score;
    int add_time;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<Student> students;
    students.reserve(10000);
    unordered_map<string, int> id_to_index;
    unordered_map<string, int> name_to_index;
    int add_counter = 0;

    bool is_sorted_id = false;
    bool is_sorted_score = false;
    vector<const Student*> sorted_by_id;
    vector<const Student*> sorted_by_score;

    int cmd;
    while (cin >> cmd) {
        if (cmd == 1) {
            string id, name;
            int score;
            cin >> id >> name >> score;
            if (id_to_index.count(id)) {
                cout << "FAILED\n";
            } else {
                students.push_back({id, name, score, add_counter});
                id_to_index[id] = students.size() - 1;
                name_to_index[name] = students.size() - 1;
                add_counter++;
                is_sorted_id = false;
                is_sorted_score = false;
                cout << "SUCCESS\n";
            }
        } else if (cmd == 2) {
            for (const auto& s : students) {
                cout << s.id << " " << s.name << " " << s.score << "\n";
            }
        } else if (cmd == 3) {
            string id;
            cin >> id;
            int idx = id_to_index[id];
            cout << students[idx].id << " " << students[idx].name << " " << students[idx].score << "\n";
        } else if (cmd == 4) {
            string name;
            cin >> name;
            int idx = name_to_index[name];
            cout << students[idx].id << " " << students[idx].name << " " << students[idx].score << "\n";
        } else if (cmd == 5) {
            if (!is_sorted_id) {
                sorted_by_id.clear();
                sorted_by_id.reserve(students.size());
                for (const auto& s : students) {
                    sorted_by_id.push_back(&s);
                }
                sort(sorted_by_id.begin(), sorted_by_id.end(), [](const Student* a, const Student* b) {
                    return a->id < b->id;
                });
                is_sorted_id = true;
            }
            for (const auto* s : sorted_by_id) {
                cout << s->id << " " << s->name << " " << s->score << "\n";
            }
        } else if (cmd == 6) {
            if (!is_sorted_score) {
                sorted_by_score.clear();
                sorted_by_score.reserve(students.size());
                for (const auto& s : students) {
                    sorted_by_score.push_back(&s);
                }
                sort(sorted_by_score.begin(), sorted_by_score.end(), [](const Student* a, const Student* b) {
                    if (a->score != b->score) {
                        return a->score > b->score;
                    }
                    return a->add_time < b->add_time;
                });
                is_sorted_score = true;
            }
            for (const auto* s : sorted_by_score) {
                cout << s->id << " " << s->name << " " << s->score << "\n";
            }
        } else if (cmd == 7) {
            cout << "END\n";
            break;
        }
    }

    return 0;
}
