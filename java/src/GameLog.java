// Вспомогательный класс для демонстрации своевременного закрытия ресурса.
public class GameLog implements AutoCloseable {
    private final String title;
    private boolean closed;

    public GameLog(String title) {
        this.title = title;
        System.out.println("[+] Журнал открыт: " + title);
    }

    public void write(String message) {
        if (closed) {
            throw new IllegalStateException("Журнал уже закрыт");
        }
        System.out.println("[Журнал] " + message);
    }

    @Override
    public void close() {
        if (!closed) {
            closed = true;
            System.out.println("[-] Журнал закрыт: " + title);
        }
    }
}
