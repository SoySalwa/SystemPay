#pragma once
#include <QTableView>
#include <QHeaderView>
#include <QVector>

namespace TableUtils
{

    // Interactive + mínimos por contenido + mínimo global
    inline void applyInteractiveMinByContents(QTableView *tv, int minGlobalPx = 24, bool recomputeOnModelChange = true)
    {
        if (!tv || !tv->model())
            return;
        auto *h = tv->horizontalHeader();
        const int cols = tv->model()->columnCount();
        if (!h || cols <= 0)
            return;

        h->setSectionResizeMode(QHeaderView::ResizeToContents);
        tv->resizeColumnsToContents();

        QVector<int> minWidths(cols);
        for (int c = 0; c < cols; ++c)
            minWidths[c] = qMax(h->sectionSize(c), minGlobalPx);

        h->setSectionResizeMode(QHeaderView::Interactive);
        h->setMinimumSectionSize(minGlobalPx);
        for (int c = 0; c < cols; ++c)
            tv->setColumnWidth(c, minWidths[c]);

        QObject::disconnect(h, nullptr, tv, nullptr);
        QObject::connect(h, &QHeaderView::sectionResized, tv, [h, minWidths, minGlobalPx](int logical, int, int now)
                         {
        const int clamp = qMax(minWidths.value(logical, minGlobalPx), minGlobalPx);
        if (now < clamp) h->resizeSection(logical, clamp); });

        if (recomputeOnModelChange)
        {
            auto recompute = [tv, minGlobalPx]()
            { applyInteractiveMinByContents(tv, minGlobalPx, true); };
            auto *m = tv->model();
            QObject::connect(m, &QAbstractItemModel::modelReset, tv, recompute);
            QObject::connect(m, &QAbstractItemModel::layoutChanged, tv, recompute);
            QObject::connect(m, &QAbstractItemModel::dataChanged, tv, [recompute](const QModelIndex &, const QModelIndex &, const QList<int> &)
                             { recompute(); });
            QObject::connect(m, &QAbstractItemModel::rowsInserted, tv, [recompute](const QModelIndex &, int, int)
                             { recompute(); });
            QObject::connect(m, &QAbstractItemModel::rowsRemoved, tv, [recompute](const QModelIndex &, int, int)
                             { recompute(); });
            QObject::connect(m, &QAbstractItemModel::columnsInserted, tv, [recompute](const QModelIndex &, int, int)
                             { recompute(); });
            QObject::connect(m, &QAbstractItemModel::columnsRemoved, tv, [recompute](const QModelIndex &, int, int)
                             { recompute(); });
        }
    }

    // Interactive + mínimos por columna + mínimo global (opcionalmente combinados con contenido)
    inline void applyInteractiveMinPerColumn(
        QTableView *tv,
        const QVector<int> &perColumnMinPx, // ≤0 = ignorar (usar contenido/global)
        int minGlobalPx = 24,
        bool includeContentAsBaseline = true)
    {
        if (!tv || !tv->model())
            return;
        auto *h = tv->horizontalHeader();
        const int cols = tv->model()->columnCount();
        if (!h || cols <= 0)
            return;

        QVector<int> content(cols, 0);
        if (includeContentAsBaseline)
        {
            h->setSectionResizeMode(QHeaderView::ResizeToContents);
            tv->resizeColumnsToContents();
            for (int c = 0; c < cols; ++c)
                content[c] = h->sectionSize(c);
        }

        QVector<int> minWidths(cols, minGlobalPx);
        for (int c = 0; c < cols; ++c)
        {
            if (c < perColumnMinPx.size() && perColumnMinPx[c] > 0)
                minWidths[c] = qMax(minWidths[c], perColumnMinPx[c]);
            if (includeContentAsBaseline)
                minWidths[c] = qMax(minWidths[c], content[c]);
        }

        h->setSectionResizeMode(QHeaderView::Interactive);
        h->setMinimumSectionSize(minGlobalPx);
        for (int c = 0; c < cols; ++c)
            tv->setColumnWidth(c, minWidths[c]);

        QObject::disconnect(h, nullptr, tv, nullptr);
        QObject::connect(h, &QHeaderView::sectionResized, tv, [h, minWidths, minGlobalPx](int logical, int, int now)
                         {
        const int clamp = qMax(minWidths.value(logical, minGlobalPx), minGlobalPx);
        if (now < clamp) h->resizeSection(logical, clamp); });
    }

} // namespace TableUtils